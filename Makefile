# this is make file to build my code
# auther = Shambhu Kumar
# date   = 25th sept. 2022

GCC = avr-gcc


clean: 
	@echo "cleaning object files"
	rm -rvf *.o
	@echo "object files cleaned"
