#pragma once

#define ATA_SR_BSY     0x80    // Busy
#define ATA_SR_DRDY    0x40    // Drive ready
#define ATA_SR_DF      0x20    // Drive write fault
#define ATA_SR_DSC     0x10    // Drive seek complete
#define ATA_SR_DRQ     0x08    // Data request ready
#define ATA_SR_CORR    0x04    // Corrected data
#define ATA_SR_IDX     0x02    // Index
#define ATA_SR_ERR     0x01    // Error

#define ATA_ER_BBK      0x80    // Bad block
#define ATA_ER_UNC      0x40    // Uncorrectable data
#define ATA_ER_MC       0x20    // Media changed
#define ATA_ER_IDNF     0x10    // ID mark not found
#define ATA_ER_MCR      0x08    // Media change request
#define ATA_ER_ABRT     0x04    // Command aborted
#define ATA_ER_TK0NF    0x02    // Track 0 not found
#define ATA_ER_AMNF     0x01    // No address mark

#define ATA_CMD_READ_PIO          0x20
#define ATA_CMD_READ_PIO_EXT      0x24
#define ATA_CMD_READ_DMA          0xC8
#define ATA_CMD_READ_DMA_EXT      0x25
#define ATA_CMD_WRITE_PIO         0x30
#define ATA_CMD_WRITE_PIO_EXT     0x34
#define ATA_CMD_WRITE_DMA         0xCA
#define ATA_CMD_WRITE_DMA_EXT     0x35
#define ATA_CMD_CACHE_FLUSH       0xE7
#define ATA_CMD_CACHE_FLUSH_EXT   0xEA
#define ATA_CMD_PACKET            0xA0
#define ATA_CMD_IDENTIFY_PACKET   0xA1
#define ATA_CMD_IDENTIFY          0xEC

#define      ATAPI_CMD_READ       0xA8
#define      ATAPI_CMD_EJECT      0x1B

#define ATA_IDENT_DEVICETYPE   0
#define ATA_IDENT_CYLINDERS    2
#define ATA_IDENT_HEADS        6
#define ATA_IDENT_SECTORS      12
#define ATA_IDENT_SERIAL       20
#define ATA_IDENT_MODEL        54
#define ATA_IDENT_CAPABILITIES 98
#define ATA_IDENT_FIELDVALID   106
#define ATA_IDENT_MAX_LBA      120
#define ATA_IDENT_COMMANDSETS  164
#define ATA_IDENT_MAX_LBA_EXT  200

#define IDE_ATA        0x00
#define IDE_ATAPI      0x01
 
#define ATA_MASTER     0x00
#define ATA_SLAVE      0x01

#define ATA_REG_DATA       0x00
#define ATA_REG_ERROR      0x01
#define ATA_REG_FEATURES   0x01
#define ATA_REG_SECCOUNT0  0x02
#define ATA_REG_LBA0       0x03
#define ATA_REG_LBA1       0x04
#define ATA_REG_LBA2       0x05
#define ATA_REG_HDDEVSEL   0x06
#define ATA_REG_COMMAND    0x07
#define ATA_REG_STATUS     0x07
#define ATA_REG_SECCOUNT1  0x08
#define ATA_REG_LBA3       0x09
#define ATA_REG_LBA4       0x0A
#define ATA_REG_LBA5       0x0B
#define ATA_REG_CONTROL    0x0C
#define ATA_REG_ALTSTATUS  0x0C
#define ATA_REG_DEVADDRESS 0x0D

// Channels:
#define      ATA_PRIMARY      0x00
#define      ATA_SECONDARY    0x01
 
// Directions:
#define      ATA_READ      0x00
#define      ATA_WRITE     0x01

#define IDE_ATA_STANDARD_PRIMARY_PORT			0x1F0
#define IDE_ATA_STANDARD_PRIMARY_CONTROL_PORT	0x3F6
#define IDE_ATA_STANDARD_SECONDARY_PORT			0x170
#define IDE_ATA_STANDARD_SECONDARY_CONTROL_PORT	0x376

#include <TTY.h>
#include <Vector.h>
#include <ASM.h>

namespace Kernel {

class IDE {
	singleton(IDE, {});
public:
	
	struct Channel {
		Channel(u32 port, u32 control_port)
            : port(port), control_port(control_port) {}
	
		u32 port;
		u32 control_port;
	
        void wait_bsy() { while (IO::read_w(port + ATA_REG_STATUS) & ATA_SR_BSY); }
        void wait_drq() { while (!(IO::read_w(port + ATA_REG_STATUS) & ATA_SR_DRDY)); }
		
        u8 detect_ata_drive(u8 bus) {
            IO::write_b(port + ATA_REG_HDDEVSEL, 0xA0 | bus << 4);

            for (int i = 0; i < 4; i++)
                IO::read_b(control_port);

            IO::write_b(port + ATA_REG_LBA0, 0);
            IO::write_b(port + ATA_REG_LBA1, 0);
            IO::write_b(port + ATA_REG_LBA2, 0);
            IO::write_b(port + ATA_REG_COMMAND, ATA_CMD_IDENTIFY);

            if (!IO::read_w(port + ATA_REG_STATUS))
                return 0;
            else {
                wait_bsy();

                if (IO::read_b(port + ATA_REG_LBA1) || IO::read_b(port + ATA_REG_LBA2))
                    return 0;

                if (IO::read_w(port + ATA_REG_STATUS) & ATA_SR_DRQ) {
                    for (int i = 0; i < 256; i++) {
                        IO::read_w(port + ATA_REG_DATA);
                    }
                    return 1;
                }
                if (IO::read_w(port + ATA_REG_STATUS) & ATA_SR_ERR)
                    return 0;
            }


		}

        void read_disk(void* dst, u8 bus, u64 lba, u16 sectors) {
            wait_bsy();

            IO::write_b(port + ATA_REG_HDDEVSEL, 0x40 | (bus << 4));

            IO::write_b(port + ATA_REG_SECCOUNT0, sectors >> 8);
            IO::write_b(port + ATA_REG_LBA0, lba >> 24);
            IO::write_b(port + ATA_REG_LBA1, lba >> 32);
            IO::write_b(port + ATA_REG_LBA2, lba >> 40);

            IO::write_b(port + ATA_REG_SECCOUNT0, sectors);
            IO::write_b(port + ATA_REG_LBA0, lba);
            IO::write_b(port + ATA_REG_LBA1, lba >> 8);
            IO::write_b(port + ATA_REG_LBA2, lba >> 16);

            IO::write_b(port + ATA_REG_COMMAND, ATA_CMD_READ_PIO_EXT);

            u16* target = (u16*)dst;

            for (u32 s = 0; s < sectors; s++) {
                wait_bsy();
                wait_drq();

                for (u32 i = 0; i < 256; i++) {
                    target[i] = IO::read_w(port + ATA_REG_DATA);
                }

                target += 256;
            }

            IO::write_b(port + ATA_REG_COMMAND, ATA_CMD_CACHE_FLUSH_EXT);
            wait_bsy();
        }

        void write_disk(void* src, u8 bus, u64 lba, u16 sectors) {
            wait_bsy();

            IO::write_b(port + ATA_REG_HDDEVSEL, 0x40 | (bus << 4));

            IO::write_b(port + ATA_REG_SECCOUNT0, sectors >> 8);
            IO::write_b(port + ATA_REG_LBA0, lba >> 24);
            IO::write_b(port + ATA_REG_LBA1, lba >> 32);
            IO::write_b(port + ATA_REG_LBA2, lba >> 40);

            IO::write_b(port + ATA_REG_SECCOUNT0, sectors);
            IO::write_b(port + ATA_REG_LBA0, lba);
            IO::write_b(port + ATA_REG_LBA1, lba >> 8);
            IO::write_b(port + ATA_REG_LBA2, lba >> 16);

            IO::write_b(port + ATA_REG_COMMAND, ATA_CMD_WRITE_PIO_EXT);

            u32* source = (u32*)src;

            for (u32 s = 0; s < sectors; s++) {
                wait_bsy();
                wait_drq();

                for (u32 i = 0; i < 256; i++) {
                    IO::write_d(port + ATA_REG_DATA, source[i]);
                }

                source += 256;
            }
        }
	};

	void initialize(u32 bar0, u32 bar1, u32 bar2, u32 bar3, u32 bar4) {
		if (!bar0 || bar0 == 1)
			bar0 = IDE_ATA_STANDARD_PRIMARY_PORT;
		if (!bar1 || bar1 == 1)
			bar1 = IDE_ATA_STANDARD_PRIMARY_CONTROL_PORT;
		if (!bar2 || bar2 == 1)
			bar2 = IDE_ATA_STANDARD_SECONDARY_PORT;
		if (!bar3 || bar3 == 1)
			bar3 = IDE_ATA_STANDARD_SECONDARY_CONTROL_PORT;
			
		m_channels.emplace(bar0, bar1);
		m_channels.emplace(bar2, bar3);

		for (auto& channel : self) {
            if (channel.detect_ata_drive(ATA_MASTER)) {
                out << "0x" << (void*)channel.port << "-MASTER: ATA Drive Detected\n";
            }
			
            if (channel.detect_ata_drive(ATA_SLAVE)) {
                out << "0x" << (void*)channel.port << "-SLAVE: ATA Drive Detected\n";
            }
        }
	}
	
	Channel& operator[](u32 i) { return m_channels[i]; }
		
	const Channel* begin() const { return m_channels.begin(); }
	const Channel* end() const { return m_channels.end(); }
	Channel* begin() { return m_channels.begin(); }
	Channel* end() { return m_channels.end(); }
	
private:
	FC::Vector<Channel> m_channels;
};

}
