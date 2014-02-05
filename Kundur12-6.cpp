#include "Grid2.hpp"
#include "MainWindow.hpp"

#include <QtWidgets/QApplication>

using namespace gw;

int main(int argc, char **argv)
{
  grid K126{"Kundur12.6"};

  substation 
    *s1 = K126.AddSubstation("One"),
    *s2 = K126.AddSubstation("Two"),
    *s3 = K126.AddSubstation("Three"),
    *s4 = K126.AddSubstation("Four"),
    *s5 = K126.AddSubstation("Five"),
    *s6 = K126.AddSubstation("Six"),
    *s7 = K126.AddSubstation("Seven"),
    *s8 = K126.AddSubstation("Eight"),
    *s9 = K126.AddSubstation("Nine"),
    *s10 = K126.AddSubstation("Ten"),
    *s11 = K126.AddSubstation("Eleven");

  bus 
    *b1L = s1->AddBus("One Low", 20),
    *b1H = s1->AddBus("One High", 230),
    *b2L= s2->AddBus("Two Low", 20),
    *b2H= s2->AddBus("Two High", 230),
    *b3L= s3->AddBus("Three Low", 20),
    *b3H= s3->AddBus("Three High", 230),
    *b4L = s4->AddBus("Four Low", 230),
    *b4H = s4->AddBus("Four High", 230),
    *b5 = s5->AddBus("Five", 230),
    *b6 = s6->AddBus("Six", 230),
    *b7 = s7->AddBus("Seven", 230),
    *b8 = s8->AddBus("Eight", 230),
    *b9 = s9->AddBus("Nine", 230),
    *b10 = s10->AddBus("Ten", 230),
    *b11 = s11->AddBus("Eleven", 230);

  transformer 
    *t1 = s1->AddTransformer("Tfmr One", b1L, b1H, {0, 0.15}, {1.0, 0}, 20, 230),
    *t2 = s2->AddTransformer("Tfmr Two", b2L, b2H, {0, 0.15}, {1.0, 0}, 20, 230),
    *t3 = s3->AddTransformer("Tfmr Three", b3L, b3H, {0, 0.15}, {1.0, 0}, 20, 230),
    *t4 = s4->AddTransformer("Tfmr Four", b4L, b4H, {0, 0.15}, {1.0, 0}, 20, 230);
   
  line
    *l5_6 = K126.AddLine("Line 5-6", b5, b6, {0.0001*25, 0.001*25}, 230),
    *l6_7 = K126.AddLine("Line 6-7", b6, b7, {0.0001*10, 0.001*10}, 230),
    *l7_8a = K126.AddLine("Line 7-8 A", b7, b8, {0.0001*110, 0.001*110}, 230),
    *l7_8b = K126.AddLine("Line 7-8 B", b7, b8, {0.0001*110, 0.001*110}, 230),
    *l8_9a = K126.AddLine("Line 8-9 A", b8, b9, {0.0001*110, 0.001*110}, 230),
    *l8_9b = K126.AddLine("Line 8-9 B", b8, b9, {0.0001*110, 0.001*110}, 230),
    *l9_10 = K126.AddLine("Line 9-10", b9, b10, {0.0001*10, 0.001*10}, 230),
    *l10_11 = K126.AddLine("Line 10-11", b10, b11, {0.0001*25, 0.001*25}, 230);

  return app.exec();
}
