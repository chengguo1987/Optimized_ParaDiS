#include "RenderWindowUISingleInheritance.h"

// This is included here because it is forward declared in
// RenderWindowUISingleInheritance.h
#include "ui_RenderWindowUISingleInheritance.h"

#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCubeSource.h>
#include <vtkSmartPointer.h>
#include <vtkPLYReader.h>
#include <vtkBox.h>
#include <vtkClipPolyData.h>
#include <vtkGeometryFilter.h>
#include <vtkSliderWidget.h>
#include <vtkCommand.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkVersion.h>
#include <vtkSelectEnclosedPoints.h>
#include <vtkRendererCollection.h>
#include <vtkPointData.h>
#include <vtkTransform.h>
#include <vtkLinearTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyData.h>
#include <vtkInteractorStyleSwitch.h>
#include <vtkCenterOfMass.h>
#include <vtkDataSet.h>

vtkStandardNewMacro(MouseInteractorStyle6);

// Define interaction style
 
void MouseInteractorStyle6::OnLeftButtonDown()
{
  std::cout << "Pressed left mouse button." << std::endl;
  // Forward events
  vtkInteractorStyleTrackballActor::OnLeftButtonDown();
}

void MouseInteractorStyle6::OnMiddleButtonUp()
{
  //std::cout << "Pressed middle mouse button." << std::endl;

  int x = this->Interactor->GetEventPosition()[0];
  int y = this->Interactor->GetEventPosition()[1];
  this->FindPokedRenderer(x, y);
  this->FindPickedActor(x, y);

  if (this->CurrentRenderer == NULL || this->InteractionProp == NULL)
    {
    std::cout << "Nothing selected." << std::endl;
    return;
    }

  vtkSmartPointer<vtkPropCollection> actors =
    vtkSmartPointer<vtkPropCollection>::New();

  this->InteractionProp->GetActors(actors);
  actors->InitTraversal();
  vtkActor* actor = vtkActor::SafeDownCast(actors->GetNextProp());

  vtkPolyData* polydata = vtkPolyData::SafeDownCast(actor->GetMapper()->GetInputAsDataSet());

  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->SetMatrix(actor->GetMatrix());

  vtkSmartPointer<vtkTransformPolyDataFilter> transformPolyData =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  transformPolyData->SetInputConnection(polydata->GetProducerPort());
#else
  transformPolyData->SetInputData(polydata);
#endif
  transformPolyData->SetTransform(transform);
  transformPolyData->Update();


  // Release interaction
  this->StopState();

}

void MouseInteractorStyle6::OnRightButtonDown()
{
  std::cout << "Pressed right mouse button." << std::endl;
  // Forward events
  vtkInteractorStyleTrackballActor::OnRightButtonDown();
}
 
// Constructor
RenderWindowUISingleInheritance::RenderWindowUISingleInheritance() 
{
  this->ui = new Ui_RenderWindowUISingleInheritance;
  this->ui->setupUi(this);

  // Set up action signals and slots
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
  connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(slotOpen())); 
  connect(this->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(slotReset()));

  
  this->ui->horizontalSlider->setRange(1, 500);
  this->ui->horizontalSlider->setValue(10);
  this->ui->horizontalSlider_2->setRange(1, 500);
  this->ui->horizontalSlider_2->setValue(10);
  this->ui->horizontalSlider_3->setRange(1, 500);
  this->ui->horizontalSlider_3->setValue(10);
  
  this->ui->spinBox->setRange(1, 500);
  this->ui->spinBox->setValue(10);
  this->ui->spinBox_2->setRange(1, 500);
  this->ui->spinBox_2->setValue(10);
  this->ui->spinBox_3->setRange(10, 500);
  this->ui->spinBox_3->setValue(10);
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
 
  //Adjust the length, width and height of the bounding box
  connect(this->ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()) );
  connect(this->ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()) );
  connect(this->ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()) );
  //Adjust the position of the bounding box
  connect(this->ui->spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()));
  connect(this->ui->spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()));
  connect(this->ui->spinBox_6, SIGNAL(valueChanged(int)), this, SLOT(slotUpdate()));

  this->reader = vtkSmartPointer<vtkPLYReader>::New();  

  this->cubeSource=vtkSmartPointer<vtkCubeSource>::New();
  this->cubeSource->SetBounds(-5, 5, -5, 5, -5, 5);

/*
  vtkSmartPointer<vtkBox> implicitCube =
    vtkSmartPointer<vtkBox>::New();
  implicitCube->SetBounds(this->cubeSource->GetOutput()->GetBounds());


  vtkSmartPointer<vtkClipPolyData> clipper=
    vtkSmartPointer<vtkClipPolyData>::New();
  clipper->SetInputConnection(this->reader->GetOutputPort());
  clipper->SetClipFunction(implicitCube);
  clipper->InsideOutOn();
  clipper->Update();

  //vtkSmartPointer<vtkGeometryFilter> geomFilter=
  //  vtkSmartPointer<vtkGeometryFilter>::New();
  //geomFilter->SetInputConnection(clipper->GetOutputPort());
*/



  // Create a mapper and actor for the clipped mesh
  vtkSmartPointer<vtkPolyDataMapper> clippedMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  clippedMapper->SetInputConnection(this->reader->GetOutputPort());
  clippedMapper->ScalarVisibilityOn();

  vtkSmartPointer<vtkActor> clippedActor = 
      vtkSmartPointer<vtkActor>::New();
  clippedActor->SetMapper(clippedMapper);

  // Create a mapper and actor for cube
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper=
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(this->cubeSource->GetOutputPort());

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

 
  // VTK/Qt wedded
  this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
  this->ui->qvtkWidget->GetRenderWindow()->SetInteractor(this->ui->qvtkWidget->GetInteractor());

  //MouseInteractorStyle6 * style =
   // MouseInteractorStyle6::New();
  //style->CubeActor = cubeActor;
 
  //this->ui->qvtkWidget->GetInteractor()->SetInteractorStyle(style);
 
  this->ui->qvtkWidget->GetInteractor()->Start();

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
   this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->Render();
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
  this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->Render();
}

void RenderWindowUISingleInheritance::slotReset()
{
  this->cubeSource->SetBounds(-5, 5, -5, 5, -5, 5);
  this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->ResetCamera();
  this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera()->SetViewUp(0.0, 1.0, 0.0);
  this->ui->horizontalSlider->setValue(10);
  this->ui->horizontalSlider_2->setValue(10);
  this->ui->horizontalSlider_3->setValue(10);
  this->ui->spinBox->setValue(10);
  this->ui->spinBox_2->setValue(10);
  this->ui->spinBox_3->setValue(10);
  this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->Render();
}

