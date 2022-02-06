CC := gcc
LIBS = -ldl -lpthread

patch:
	$(CC) -fPIC $(LIBS) -c -o basspatch.o basspatch.c
	$(CC) -shared $(LIBS) -o basspatch.so basspatch.o