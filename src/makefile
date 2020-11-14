OBJS =	main.o\
	Shell.o\
	cd.o\
	grep.o\
	hist.o\
	ls.o\
	mkdir.o\
	nf.o\
	nfe.o\
	pipe.o\
	pwd.o\
	rmdir.o\
	touch.o\
	wc.o\

main: ${OBJS}
$.o : $.c
	gcc -c $^ -o $@

.PHONY:clean
clean:
	# Move the executive file "main" to the root path
	mv ./main ../main
	# Clean all the .o files
	rm -rf $(OBJS)
	

