cmd_/home/network/MyUniversity/ModuleProgramming/hello.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/network/MyUniversity/ModuleProgramming/hello.ko /home/network/MyUniversity/ModuleProgramming/hello.o /home/network/MyUniversity/ModuleProgramming/hello.mod.o