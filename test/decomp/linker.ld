/* Lays the decompiler fixtures out as a synthetic Sigma lens image: file offset equals
   address, a "CHIPINFORMATION" header at 0x7fc0 so SigmaFirmwareLoader takes the image,
   and the jmpf vector table at the flash base, followed by the fixture code. */
OUTPUT_FORMAT("elf32-xstormy16")
ENTRY(vectors)
SECTIONS
{
	.image 0 : {
		BYTE(0)
		. = 0x7fc0;
		KEEP(*(.chipinfo))
		. = 0x8000;
		KEEP(*(.vectors))
		*(.text)
	} = 0
	/DISCARD/ : { *(.data) *(.bss) }
}
