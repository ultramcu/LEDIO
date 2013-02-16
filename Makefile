
APP_DIR= $(PWD)

GCC=gcc


SRC_LIST =  main_led.c
INC_LIST = -L/store/lib/bcm2835-1.14/src/
LIB_LIST =  -lbcm2835 -lrt

GCCFLAG = 
APP_NAME= run

all:	
	rm -f $(APP_NAME)
	date 
	$(GCC) -o $(APP_NAME) $(SRC_LIST) $(INC_LIST) $(LIB_LIST)

clean:
	rm -f $(APP_NAME) 


