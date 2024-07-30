CXX = g++

PROJ = snake
OBJS = main.o model.o view.o controller.o
RM = rm

$(PROJ): $(OBJS)
$(CXX) $(OBJS) -o $(PROJ)

clean:
	$(RM) $(OBJS) $(PROJ)

-include.depence:

depend: 
	$(CXX) -MM $(OBJS:.o=.cc) > .depence