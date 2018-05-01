ZBuffer.o: ZBuffer.cc ZBuffer.h easy_image.h 2D_L-systemen.h Line2D.h \
 Point2D.h Color.h ini_configuration.h l_parser.h 3D_LineDrawings.h \
 vector3d.h Figure.h Face.h Light.h
	$(CC) $(CXXFLAGS) -c $< -o $@
