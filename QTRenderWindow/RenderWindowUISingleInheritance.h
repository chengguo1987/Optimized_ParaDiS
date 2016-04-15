#ifndef RenderWindowUISingleInheritance_H
#define RenderWindowUISingleInheritance_H
 
#include <vtkSmartPointer.h>
#include <vtkPLYReader.h>
#include <vtkCubeSource.h>

#include <QMainWindow>
#include <QFileDialog> 


// Forward Qt class declarations
class Ui_RenderWindowUISingleInheritance;
 
class RenderWindowUISingleInheritance : public QMainWindow
{
  Q_OBJECT
public:
 
  // Constructor/Destructor
  RenderWindowUISingleInheritance(); 
  ~RenderWindowUISingleInheritance() {};

 
public slots:

  virtual void slotExit();
  virtual void slotOpen();
  virtual void slotUpdate();

private:
 
  // Designer form
  vtkSmartPointer<vtkPLYReader> reader;
  vtkSmartPointer<vtkCubeSource> cubeSource;
  Ui_RenderWindowUISingleInheritance *ui;
};
 
#endif
