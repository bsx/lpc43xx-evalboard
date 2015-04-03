MEMORY
{
  sram1 (rwx) : ORIGIN = 0x00000000, LENGTH = 32K
  sram2 (rwx) : ORIGIN = 0x10080000, LENGTH = 32K
}

ram_top = ORIGIN(sram2) + LENGTH(sram2);
ENTRY(boot_entry)

SECTIONS
{
    .text : {
        KEEP(*(.irq-vectors))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } >sram1

    .data :
    {
        _data = .;
        *(.data*)
        _edata = .;
    } >sram1

    .bss : {
        _bss = .;
        *(.bss)
        _ebss = .;
    } >sram2

    end = .;

    stack_entry = ram_top;
}
