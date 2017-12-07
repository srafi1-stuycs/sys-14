ctl: ctl.c
	gcc ctl.c -o ctl
run: ctl
	./ctl
clean: ctl
	rm ctl
