engine.o: engine.cc easy_image.h ini_configuration.h 2D_L-systemen.h \
 Line2D.h Point2D.h Color.h l_parser.h 3D_LineDrawings.h vector3d.h \
 Figure.h Face.h 3D_Figures.h 3D_L-systemen.h ZBuffer.h Light.h
	$(CC) $(CXXFLAGS) -c $< -o $@
