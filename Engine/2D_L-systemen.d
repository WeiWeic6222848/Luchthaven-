2D_L-systemen.o: 2D_L-systemen.cc 2D_L-systemen.h Line2D.h Point2D.h \
 Color.h easy_image.h ini_configuration.h l_parser.h ZBuffer.h \
 3D_LineDrawings.h vector3d.h Figure.h Face.h
	$(CC) $(CXXFLAGS) -c $< -o $@
