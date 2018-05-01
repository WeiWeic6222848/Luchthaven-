Light.o: Light.cc Light.h Color.h vector3d.h
	$(CC) $(CXXFLAGS) -c $< -o $@
