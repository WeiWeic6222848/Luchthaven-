3D_LineDrawings.o: 3D_LineDrawings.cc 3D_LineDrawings.h vector3d.h \
 Figure.h Face.h Color.h 2D_L-systemen.h Line2D.h Point2D.h easy_image.h \
 ini_configuration.h l_parser.h
	$(CC) $(CXXFLAGS) -c $< -o $@
