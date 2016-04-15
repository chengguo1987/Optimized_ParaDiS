#include "RenderWindowUISingleInheritance.h"

// This is included here because it is forward declared in
// RenderWindowUISingleInheritance.h
#include "ui_RenderWindowUISingleInheritance.h"

#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkSmartPointer.h>
#include <vtkPLYReader.h>
#include <vtkBox.h>
#include <vtkClipPolyData.h>
#include <vtkGeometryFilter.h>
#include <vtkSliderWidget.h>
#include <vtkCommand.h>
#include <vtkProperty.h>

 
// Constructor
RenderWindowUISingleInheritance::RenderWindowUISingleInheritance() 
{
  this->ui = new Ui_RenderWindowUISingleInheritance;
  this->ui->setupUi(this);

  // Set up action signals and slots
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
  connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(slotOpen())); 

  
  this->ui->horizontalSlider->setRange(1, 200);
  this->ui->horizontalSlider->setValue(1);
  this->ui->horizontalSlider_2->setRange(1, 200);
  this->ui->horizontalSlider_2->setValue(1);
  this->ui->horizontalSlider_3->setRange(1, 200);
  this->ui->horizontalSlider_3->setValue(1);
  
  this->ui->spinBox->setRange(1, 200);
  this->ui->spinBox->setValue(1);
  this->ui->spinBox_2->setRange(1, 200);
  this->ui->spinBox_2->setValue(1);
  this->ui->spinBox_3->setRange(1, 200);
  this->ui->spinBox_3->setValue(1);
  this->ui->spinBox_4->setRange(-200,200);
  this->ui->spinBox_4->setValue(0);
  this->ui->spinBox_5->setRange(-200,200);
  this->ui->spinBox_5->setValue(0);
  this->ui->spinBox_6->setRange(-200,200);
  this->ui->spinBox_6->setValue(0);

  connect(this->ui->horizontalSlider, SIGNAL(valueChanged(int)), this->ui->spinBox, SLOT(setValue(int)));
  connect(this->ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this->ui->spinBox_2, SLOT(setValue(int)));
  connect(this->ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this->ui->spinBox_3, SLOT(setValue(int)));
  connect(this->ui->spinBox, SIGNAL(valueChanged(int)), this->ui->horizontalSlider, SLOT(setValue(int)));
  connect(this->ui->spinBox_2, SIGNAL(valueChanged(int)), this->ui->horizontalSlider_2, SLOT(setValue(int)));
  connect(this->ui->spinBox_3, SIGNAL(valueChanged(int)), this->ui->horizontalSlider_3, SLOT(setValue(int)));
 
  this->reader = vtkSmartPointer<vtkPLYReader>::New();  

  this->cubeSource=vtkSmartPointer<vtkCubeSource>::New();
  this->cubeSource->SetXLength(10);
  this->cubeSource->SetYLength(10);
  this->cubeSource->SetZLength(10);

 

  printf("X is %lf, Y is %lf, Z is %lf", cubeSource->GetXLength(), cubeSource->GetYLength(), cubeSource->GetZLength());

  //Adjust the length, width and height of the bounding box
  connect(this->ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()) );
  connect(this->ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()) );
  connect(this->ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()) );
  //Adjust the position of the bounding box
  connect(this->ui->spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()));
  connect(this->ui->spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()));
  connect(this->ui->spinBox_6, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()));


  vtkSmartPointer<vtkBox> implicitCube =
    vtkSmartPointer<vtkBox>::New();
  implicitCube->SetBounds(this->cubeSource->GetOutput()->GetBounds());


  // Clipping Filters
  
  vtkSmartPointer<vtkClipPolyData> clipper=
    vtkSmartPointer<vtkClipPolyData>::New();
  clipper->SetInputConnection(this->reader->GetOutputPort());
  clipper->SetClipFunction(implicitCube);
  clipper->InsideOutOn();
  clipper->Update();

  //vtkSmartPointer<vtkGeometryFilter> geomFilter=
  //  vtkSmartPointer<vtkGeometryFilter>::New();
  //geomFilter->SetInputConnection(clipper->GetOutputPort());

  // Create a mapper and actor for the clipped mesh
  vtkSmartPointer<vtkPolyDataMapper> clippedMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  clippedMapper->SetInputConnection(reader->GetOutputPort());
  clippedMapper->ScalarVisibilityOn();

  vtkSmartPointer<vtkActor> clippedActor = 
      vtkSmartPointer<vtkActor>::New();
  clippedActor->SetMapper(clippedMapper);

  // Create a mapper and actor for cube
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper=
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

  vtkSmartPointer<vtkActor> cubeActor=
    vtkSmartPointer<vtkActor> ::New();
  cubeActor->SetMapper(cubeMapper);
  cubeActor->GetProperty()->SetRepresentationToWireframe();
  cubeActor->GetProperty()->SetOpacity(0.2);

 
  // VTK Renderer
  vtkSmartPointer<vtkRenderer> renderer = 
      vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(clippedActor);
  renderer->AddActor(cubeActor);
  renderer->SetBackground(.2, .3, .2);


  renderer->ResetCamera();
  renderer->ResetCameraClippingRange();
 
  // VTK/Qt wedded
  this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
  this->ui->qvtkWidget->GetRenderWindow()->SetInteractor(this->ui->qvtkWidget->GetInteractor());

 }

void RenderWindowUISingleInheritance::slotExit() 
{
  qApp->exit();
}

void RenderWindowUISingleInheritance::slotOpen()
{
  QString filename = QFileDialog::getOpenFileName(
  		this,
		tr("Open File"),
		"/",
		"All files (*.*);;PLY files (*.ply)"
		); 
   this->reader->SetFileName(filename.toStdString().c_str());
}

void RenderWindowUISingleInheritance::slotUpdate()
{
  this->cubeSource->SetXLength(this->ui->horizontalSlider->value());
  this->cubeSource->SetYLength(this->ui->horizontalSlider_2->value());
  this->cubeSource->SetZLength(this->ui->horizontalSlider_3->value());
  double center_x = this->ui->spinBox_4->value();
  double center_y = this->ui->spinBox_5->value();
  double center_z = this->ui->spinBox_6->value();
  this->cubeSource->SetCenter(center_x, center_y, center_z);
  this->cubeSource->Update();
}


