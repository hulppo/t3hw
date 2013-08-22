#Used for determing the object files
SRCS = Message.cpp ChannelMessage.cpp PrivateMessage.cpp \
	Command.cpp ServerCommand.cpp ChannelCommand.cpp \
	Connection.cpp SimpleBotConnection.cpp \
	User.cpp Database.cpp Channel.cpp \
	Server.cpp SynchronizedObject.cpp \
	SynchronizedMap.cpp MathBotConnection.cpp \
	RandomBotConnection.cpp #ConnectionHandler.cpp
	 #CLConnection.cpp #Has to be compiled with mico-c++

INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))

EXE = server

CXX = g++

CPPFLAGS = -Wall -c -I $(INC_DIR)

LDFLAGS = -lpthread

#This is made when make is called without params
all:	$(EXE)
	@echo -e "Everything up to date"



freebsd: $(OBJS)
	@echo "Linking executable $(EXE) for FreeBSD"
	@$(CXX) -pthread -o $(EXE) $(OBJS)

$(EXE):	$(OBJS) corba
	@echo -e "Linking executable $(EXE)"
	@$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS)

corba:	$(OBJS) obj/CHAdapter_impl.o obj/CHAdapter.o \
	obj/ConnectionAdapter_impl.o obj/ConnectionAdapter.o \
	obj/ClientAdapter.o obj/CLConnection.o
	@echo -e "Linking executable $(EXE) with CORBA support"
	@mico-ld -pthread -I inc -o $(EXE) \
	$(OBJS) obj/CHAdapter_impl.o obj/CHAdapter.o \
	obj/ConnectionAdapter_impl.o \
	obj/ConnectionAdapter.o obj/ClientAdapter.o \
	obj/CLConnection.o \
	-lmico2.3.9

client: obj/Client.o obj/CHAdapter.o obj/ConnectionAdapter.o \
	obj/ClientAdapter.o obj/ClientAdapter_impl.o
	@echo -e "Linking client program"
	@mico-ld -pthread \
	-o client obj/Client.o obj/CHAdapter.o  obj/ConnectionAdapter.o \
	obj/ClientAdapter.o obj/ClientAdapter_impl.o \
	-lmico2.3.9

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	@echo -e "\tCompiling: $< --> $@"
	@$(CXX) $(CPPFLAGS) -c -o $@ $<


obj/CLConnection.o: inc/CLConnection.h src/CLConnection.cpp
	mico-c++ -Iinc -c src/CLConnection.cpp -o obj/CLConnection.o

obj/CHAdapter_impl.o: inc/CHAdapter.h inc/CHAdapter_impl.h src/CHAdapter_impl.cc
	mico-c++ -Iinc -c src/CHAdapter_impl.cc -o obj/CHAdapter_impl.o

obj/CHAdapter.o: inc/CHAdapter.h src/CHAdapter.cc
	mico-c++ -Iinc -c src/CHAdapter.cc -o obj/CHAdapter.o

obj/ConnectionAdapter_impl.o: inc/ConnectionAdapter_impl.h src/ConnectionAdapter_impl.cc
	mico-c++ -Iinc -c src/ConnectionAdapter_impl.cc -o obj/ConnectionAdapter_impl.o


obj/ConnectionAdapter.o: inc/ConnectionAdapter.h src/ConnectionAdapter.cc
	mico-c++ -Iinc -c src/ConnectionAdapter.cc -o obj/ConnectionAdapter.o

obj/Client.o: src/Client.cpp
	mico-c++ -Iinc -c src/Client.cpp -o obj/Client.o

obj/ClientAdapter_impl.o: src/ClientAdapter_impl.cc inc/ClientAdapter_impl.h
	mico-c++ -Iinc -c src/ClientAdapter_impl.cc -o obj/ClientAdapter_impl.o

obj/ClientAdapter.o: src/ClientAdapter.cc inc/ClientAdapter.h
	mico-c++ -Iinc -c src/ClientAdapter.cc -o obj/ClientAdapter.o


clean:
	@-rm $(OBJS) $(EXE)
	@-rm obj/*.o
	@-rm client
	@echo -e "Cleanup successful"

.PHONY: all clean
