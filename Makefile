CC := gcc
LIBS = -ldl -lpthread

patch:
	$(CC) basspatch.c -O3 -fPIC -shared $(LIBS) -o basspatch.so