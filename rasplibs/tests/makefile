RASPLIBS=/home/pi/rasplibs/lib
RASPINC=/home/pi/rasplibs/inc

all:
	gcc main.c -I$(RASPINC) $(RASPLIBS)/precompile.c $(RASPLIBS)/functor.c  $(RASPLIBS)/algo.c  $(RASPLIBS)/reverse.s $(RASPLIBS)/isort.s $(RASPLIBS)/icopy.s $(RASPLIBS)/isequal.s  -std=c11 -ggdb -o test
