obj = command.o commands.o config_file.o contest.o problem.o memory.o result.o where.o test.o main.o

CXXFLAGS = -O2

tester : $(obj)
	g++ $(obj) -o $@

