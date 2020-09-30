#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cstring>

#include <ArgumentHandler.h>


typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef double f64;
typedef float f32;

#define PACKED __attribute__((packed))


struct PACKED FS_VolumeDescriptor {
	char signature[8]	= "FOS2_FS";
	u8 version_major	= 0;
	u8 version_minor	= 0;

	char vol_name[24]	= "FOS2 Boot Volume";
	char os_name[16]	= "Linux x84_64";

	u32 block_size		= 512;

	u64 vol_start_lba	= 0;
	u64 vol_end_lba		= 0;

	u64 root_dir_block	= 2;
};


struct PACKED FS_DirectoryDescriptor {
	u32 entries		= 0;
	u64 start_block	= 0;
	u64 next_block	= 0;
};


struct PACKED FS_DirectoryEntryDescriptor {
	u8 type			= 0;
	u64 block		= 0;
	char name[24];
};


struct PACKED FS_FileDescriptor {
	u64 blocks		= 0;
	u64 start_block	= 0;
	u64 next_block	= 0;
};


enum EntryType {
	FS_ENTRY_FILE	= 0,
	FS_ENTRY_DIR	= 1,
};


void align_fstream(std::ofstream& file, long align) {
	long pos = file.tellp();
	long bytes = align - (pos % align);
	file << std::string(bytes, '\0');
}

FS_DirectoryEntryDescriptor add_path(std::ofstream& out, const std::string path) {
	std::filesystem::directory_entry path_entry(path);

	if (path_entry.is_regular_file()) {
		std::cout << "Copying file '" << path_entry.path().filename().c_str() << "'" << std::endl;

		FS_FileDescriptor fsfd;

		u32 fsfd_block = out.tellp() / 512;
		fsfd.start_block = fsfd_block + 1;
		fsfd.blocks = (path_entry.file_size() / 512) + 1;

		out.write((char*)&fsfd, sizeof(fsfd));
		align_fstream(out, 512);

		out << std::ifstream(path).rdbuf();
		align_fstream(out, 512);

		FS_DirectoryEntryDescriptor fsded = {FS_ENTRY_FILE, fsfd_block, ""};
		strncpy(fsded.name, path_entry.path().filename().c_str(), sizeof(fsded.name));
		return fsded;
	}

	else if (path_entry.is_directory()) {
		std::cout << "Entered directory '" << path_entry.path().filename().c_str() << "/'" << std::endl;

		FS_DirectoryDescriptor fsdd;
		std::vector<FS_DirectoryEntryDescriptor> fsded_vec;

		for (auto& entry : std::filesystem::directory_iterator(path)) {
			fsded_vec.push_back(add_path(out, entry.path()));
		}

		u64 fsdd_block = out.tellp() / 512;
		fsdd.start_block = fsdd_block + 1;
		fsdd.entries = fsded_vec.size();

		out.write((char*)&fsdd, sizeof(fsdd));
		align_fstream(out, 512);

		for (const FS_DirectoryEntryDescriptor& fsded : fsded_vec)
			out.write((const char*)&fsded, sizeof(fsded));
		align_fstream(out, 512);

		FS_DirectoryEntryDescriptor fsded = {FS_ENTRY_DIR, fsdd_block, ""};
		strncpy(fsded.name, path_entry.path().filename().c_str(), sizeof(fsded.name));
		std::cout << "Left directory '" << path_entry.path().filename().c_str() << "/'" << std::endl;
		return fsded;
	}

	else
		throw std::runtime_error("mkfsimg: unkown error in add_path()");
}

int main(int argc, char** argv) {
	std::string out_path = "out.img";
	std::string bootsector_path = "";
	std::string volume_name = "FOS2 Boot Volume";

	ArgumentHandler ah;
	ah.AddSwitch("-o", &out_path);
	ah.AddSwitch("-b", &bootsector_path);
	ah.AddSwitch("--volume-name", &volume_name);

	std::vector<std::string> in_files = ah.Args(argc, argv);

	if (!in_files.size()) {
		std::cout << "mkfsimg: error: no input files" << std::endl;
		return 1;
	}

	std::ofstream out(out_path);

	if (!out.good() || !out.is_open()) {
		std::cout << "mkfsimg: error: failed to open output file" << std::endl;
		return 1;
	}

	if (bootsector_path != "") {
		char buf[512];
		std::ifstream bootsector_file(bootsector_path);
		if (!bootsector_file.good() || !bootsector_file.is_open()) {
			std::cout << "mkfsimg: error: failed to open '" << bootsector_path << "'" << std::endl;
			return 1;
		}

		bootsector_file.read(buf, 512);
		out.write(buf, 512);
	}

	out << std::string(512, '\0');

	FS_DirectoryDescriptor fsdd;
	std::vector<FS_DirectoryEntryDescriptor> fsded_vec;

	for (const std::string& in_path : in_files) {
		fsded_vec.push_back(add_path(out, in_path));
	}

	u64 fsdd_block = out.tellp() / 512;
	fsdd.start_block = fsdd_block + 1;
	fsdd.entries = fsded_vec.size();

	out.write((char*)&fsdd, sizeof(fsdd));
	align_fstream(out, 512);

	for (const FS_DirectoryEntryDescriptor& fsded : fsded_vec)
		out.write((const char*)&fsded, sizeof(fsded));
	align_fstream(out, 512);

	out.seekp(512, std::ios_base::beg);

	FS_VolumeDescriptor fsvd;
	fsvd.root_dir_block = fsdd_block;
	memset(fsvd.vol_name, 0, sizeof(fsvd.vol_name));
	strncpy(fsvd.vol_name, volume_name.c_str(), sizeof(fsvd.vol_name));

	out.write((char*)&fsvd, sizeof(fsvd));
	align_fstream(out, 512);

	return 0;
}
