#ifndef RenderWindowUISingleInheritance_H
#define RenderWindowUISingleInheritance_H
 
#include <vtkSmartPointer.h>
#include <vtkPLYReader.h>
#include <vtkCubeSource.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkObjectFactory.h>
//#include <vtkPolyData.h>

#include <QMainWindow>
#include <QFileDialog> 


// Forward Qt class declarations
class Ui_RenderWindowUISingleInheritance;

class MouseInteractorStyle6 : public vtkInteractorStyleTrackballActor
{
public:
  vtkPolyData* Sphere;
  vtkActor* CubeActor;
  static MouseInteractorStyle6* New();
  vtkTypeMacro(MouseInteractorStyle6, vtkInteractorStyleTrackballActor);
  virtual void OnLeftButtonDown();
  virtual void OnMiddleButtonUp();
  virtual void OnRightButtonDown();
};
 
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
  virtual void slotReset();
private:
 
  // Designer form
  vtkSmartPointer<vtkPLYReader> reader;
  vtkSmartPointer<vtkCubeSource> cubeSource;
  Ui_RenderWindowUISingleInheritance *ui;
};
 
#endif
