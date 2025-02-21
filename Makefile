#####################################################
#Copyright @ Information processing Center of Network and Switching State Key Lab of BUPT
#        2015-3-15     日期:11:48:44
#Name of file:hh.cpp
#Purpose:
#Author: Xuzhen Zhu
#Contact zxz430@sina.com
#History: v1
######################################################

all: compile

#macro virables
Target = double_infec
CC = g++
CPPFLAGS = -O2 -Wall
IFLAGS = -I include/
LFLAGS = 
OBJS = src/network/ER_network.o src/network/SF_network.o\
src/network/network_basic_ops.o src/utils/random_util.o src/utils/edge_weight.o 


compile: $(Target)

clean:
	rm -rf $(Target) $(OBJS)  src/double_infection.o 

sf_clean:
	rm -rf sf_double $(OBJS)  src/SF_double_infection.o 

er_sf_clean:
	rm -rf sf_double $(OBJS)  src/ER_SF_double_infection.o 

#dependency commands
#infection_target
$(Target):  $(OBJS) src/double_infection.o 
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@  $(OBJS) src/double_infection.o 

sf_double: $(OBJS) src/SF_double_infection.o 
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@  $(OBJS) src/SF_double_infection.o

er_sf_double:$(OBJS) src/ER_SF_double_infection.o
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@  $(OBJS) src/ER_SF_double_infection.o

src/network/ER_network.o: src/network/ER_network.cpp
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@ -c $<
	
src/network/SF_network.o: src/network/SF_network.cpp
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@ -c $<	
	
src/network/network_overlay_ops.o: src/network/network_overlay_ops.cpp
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@ -c $<	

src/network/network_basic_ops.o: src/network/network_basic_ops.cpp
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@ -c $<	
	
src/utils/random_util.o: src/utils/random_util.cpp
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@ -c $<
	
src/utils/edge_weight.o: src/utils/edge_weight.cpp
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@ -c $<

src/double_infection.o : src/double_infection.cpp
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@ -c $<

src/SF_double_infection.o : src/SF_double_infection.cpp
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@ -c $<
	
src/ER_SF_double_infection.o : src/ER_SF_double_infection.cpp
	$(CC) $(CPPFLAGS) $(IFLAGS) $(LFLAGS) -o $@ -c $<