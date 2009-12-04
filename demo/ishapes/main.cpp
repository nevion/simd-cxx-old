/*
 * File:   main.cpp
 * Author: corsaro
 *
 * Created on July 12, 2009, 6:49 PM
 */

#include <QtGui/QApplication>
#include <ShapesDialog.hpp>
#include <stdlib.h>
#include <time.h>

#include <dds/runtime.hpp>

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    std::string partition("");

    if (argc > 1)
        partition = argv[1];
    
    dds::Runtime::start(partition);
    srand(clock());
    QApplication app(argc, argv);

    // create and show your widgets here
    ShapesDialog shapes;
    shapes.show();
    int retval = app.exec();
    dds::Runtime::stop();
    return retval;
}

