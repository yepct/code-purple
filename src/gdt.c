#include "gdt.h"

//global array and ptr for gdt
struct gdt_entry_t gdt_entries[3];
struct gdt_ptr_t   gdt_ptr;

//declare flush function
extern void gdt_flush(uint32_t);

//fuck you, inventor of GDT
/* Function to setup an entry in the GDT - this one took me ages to 
   figure out, but essentially takes the necessary values for the GDT 
   and packs them into the questionable ass format required by the processor */
static void gdt_set_gate(int32_t pos, uint32_t base, uint32_t limit,
		uint8_t access, uint8_t flags){

	//separate base into high, mid, low
	gdt_entries[pos].base_low  = (base & 0xFFFF);
	gdt_entries[pos].base_mid  = (base >> 16) & 0xFF;
	gdt_entries[pos].base_high = (base >> 24) & 0xFF;

	//now to chop up the limit and granularity entries
	gdt_entries[pos].limit_low   = (limit & 0xFFFF);

	//first 4 bits of the GDT granularity entry are the high of the 20 bit limit
	gdt_entries[pos].granularity = (limit >> 16) & 0x0F;
	
	//last four bits have to be appended with bitwise OR to represent flags
	gdt_entries[pos].granularity |= gran & 0xF0;

	//the access byte is directly set from the procedure arg
	gdt_entries[pos].access      = access;
	
}

