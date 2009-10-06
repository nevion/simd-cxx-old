/* 
 * File:   DDSShapeDynamics.cpp
 * Author: corsaro
 * 
 * Created on July 13, 2009, 8:44 AM
 */

#include "DDSShapeDynamics.hpp"
#include <iostream>
extern char* colorString_[];
//extern QColor  color_[];


DDSShapeDynamics::DDSShapeDynamics(int x0, int y0,
                     simd::DataReader<ShapeType>& shapeReader,
                     const std::string& color,
                     int colorIdx)
    :   ShapeDynamics(x0, y0, QRect(0, 0, 0, 0)),
        x0_(x0),
        y0_(y0),
        shapeReader_(shapeReader),
        attached_(false),
        color_(color),
        colorIdx_(colorIdx)
{
    colorList_[BLUE] = QColor(0x33, 0x66, 0x99);
    colorList_[RED] = QColor(0xCC, 0x33, 0x33);
    colorList_[GREEN] = QColor(0x99, 0xCC, 0x66);
    colorList_[ORANGE] = QColor(0xFF, 0x99, 0x33);
    colorList_[YELLOW] = QColor(0xFF, 0xFF, 0x66);
    colorList_[MAGENTA] = QColor(0xCC, 0x99, 0xCC);
    colorList_[CYAN] = QColor(0x99, 0xCC, 0xFF);
    colorList_[BLACK] = QColor(0x33, 0x33, 0x33);
}

DDSShapeDynamics::~DDSShapeDynamics() {
}

void
DDSShapeDynamics::simulate() {
    ShapeTypeSeq samples;
    DDS::SampleInfoSeq infos;

    shapeReader_->read(samples, 
                      infos,
                       	 DDS::LENGTH_UNLIMITED,
			 DDS::ANY_SAMPLE_STATE,
			 DDS::ANY_VIEW_STATE,
			 DDS::ANY_INSTANCE_STATE);

    if (samples.length() > 0) {
        int sampleIndex = -1;
        int i = 0;
        while (i < samples.length() && sampleIndex == -1) {
            if (strcmp(samples[i].color, color_.c_str()) == 0)
                sampleIndex = i;
            ++i;
        }

        if (sampleIndex != -1) {
            pos_.rx() = samples[sampleIndex].x*2.08333F;
            pos_.ry() = samples[sampleIndex].y*2.22223F;
            
            if (attached_ == false) {
                attached_ = true;
                // std::cout << "Setting Brush to Paint in " << colorIdx_ << std::endl;
                QBrush brush = QBrush(colorList_[colorIdx_], Qt::DiagCrossPattern);
                shape_->setBrush(brush);
                QRect bounds(0,0, samples[sampleIndex].shapesize, samples[sampleIndex].shapesize);
                shape_->setBounds(bounds);
            }
        }
    }
    shapeReader_->return_loan(samples, infos);
}
