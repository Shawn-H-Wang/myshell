OBJS =	main.o\
	Shell.o\
	cd.o\
	grep.o\
	hist.o\
	ls.o\
	mkdir.o\
	rmdir.o\
	nf.o\
	nfe.o\
	pipe.o\
	pwd.o\
	rmdir.o\
	touch.o\
	wc.o\
	cat.o\
	cp.o\
	mv.o\
	rm.o\
	touch.o\

main: ${OBJS}
$.o : $.c
	gcc -c $^ -o $@

.PHONY:clean
clean:
	# Move the executive file "main" to the root path
	mv ./main ../main
	# Clean all the .o files
	rm -rf $(OBJS)
	
