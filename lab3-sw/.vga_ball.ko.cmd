cmd_/root/EmbeddedSystems/lab3-sw/vga_ball.ko := ld -r  -EL -T ./scripts/module-common.lds -T ./arch/arm/kernel/module.lds  --build-id  -o /root/EmbeddedSystems/lab3-sw/vga_ball.ko /root/EmbeddedSystems/lab3-sw/vga_ball.o /root/EmbeddedSystems/lab3-sw/vga_ball.mod.o ;  true
