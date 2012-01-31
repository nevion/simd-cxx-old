/*
 * File:   main.cpp
 * Author: corsaro
 *
 * Created on July 12, 2009, 6:49 PM
 */

#include <ShapesDialog.hpp>
#include <QtGui/QApplication>
#include <stdlib.h>
#include <time.h>

#include <dds/runtime.hpp>

int main(int argc, char *argv[]) {
  std::string partition("");
  int domainId = 0;
  if (argc > 1) {
    sscanf(argv[1], "%d", &domainId);
  }
  if (argc > 2) {
    partition = argv[2];
  }
  std::cout << "Connecting to:\n\tdomain = " << domainId  
	    << "\n\tpartition = " << partition << std::endl;
    
  dds::Runtime runtime(partition, domainId);
    
  srand(clock());
  QApplication app(argc, argv);
  Q_INIT_RESOURCE(ishape);
  // create and show your widgets here
  ShapesDialog shapes;
  shapes.show();
  int retval = app.exec();

  return retval;
}

