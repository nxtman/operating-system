ENTRY(start)

SECTIONS {
	. = 1M;

	.boot ALIGN (0x1000) :
	{
		*(.boot)
	}

	.text ALIGN (0x1000) :
	{
		*(.text)
	}

	.rodata ALIGN (0x1000) :
	{
		*(.rodata)
	}

	.bss ALIGN (0x1000) :
	{
		*(.bss)
	}
}
