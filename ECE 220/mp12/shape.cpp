#include "shape.hpp"
//Base class
//Please implement Shape's member functions
//constructor, getName()
//Implementing getName().
string Shape::getName(){return name_;}
//Implementing constructor.
Shape::Shape(string name){name_ = name;}
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}
//Implementing the constructor.
Rectangle::Rectangle(double width, double length):Shape("Rectangle"){
  width_ = width;
  length_ = length;
}
//Implementing getArea().
double Rectangle::getArea()const{return getWidth() * getLength(); }
//Implementing getVolume().
double Rectangle::getVolume()const{return 0;}
//Implementing "+".
Rectangle Rectangle::operator + (const Rectangle& rec){
 return Rectangle(width_ + (rec.getWidth()), length_ + (rec.getLength()));
}
//Implementing "-".
Rectangle Rectangle::operator - (const Rectangle& rec){
  double final_length = (0 > length_ - (rec.getLength()))? 0 : length_ - (rec.getLength());
  double final_width = (0 > width_ - (rec.getWidth()))? 0 : width_ - (rec.getWidth());
  return Rectangle(final_width, final_length);
}

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
double Circle::getRadius()const{return radius_;}
//Implementing constuctor.
Circle::Circle(double radius):Shape("Circle"){radius_ = radius;}
//Implementing getArea().
double Circle::getArea()const{return 3.1415926535 * getRadius() * getRadius();}
//Implementing getVolume().
double Circle::getVolume()const{return 0;}
//Implementing operator +.
Circle Circle::operator + (const Circle& cir){
return Circle(radius_ + (cir.getRadius()));
}
//Implementing operator -.
Circle Circle::operator - (const Circle& cir){
double final_radius = (0 > radius_ - (cir.getRadius())) ? 0 : radius_ - (cir.getRadius());
return Circle(final_radius);
}
//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
double Sphere::getRadius()const{return radius_;}
//Implementing the constructor.
Sphere::Sphere(double radius):Shape("Sphere"){radius_ = radius;}
//Implementing getArea().
double Sphere::getArea()const{return 4*3.1415926535*getRadius()*getRadius();}
//Implementing getVolume().
double Sphere::getVolume()const{return 4.0 / 3.0 * getRadius() * getRadius() * getRadius() * 3.1415926535;}
//Implementing operator +.
Sphere Sphere::operator + (const Sphere& sph){return Sphere(radius_ + (sph.getRadius())); }
//Implementing operator -.
Sphere Sphere::operator - (const Sphere& sph){
  double final_radius = (0 > radius_ - (sph.getRadius())) ? 0: radius_ - (sph.getRadius());
  return Sphere(final_radius);
}
//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}
//Implementing constructor.
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism"){
  width_ = width;
  length_ = length;
  height_ = height;
}
//Implementing getArea().
double RectPrism::getArea()const{
  return 2* (getLength() * getWidth() + getLength() * getHeight() + getWidth() * getHeight());
}
//Implementing getVolume().
double RectPrism::getVolume()const{
  return getLength() * getWidth() * getHeight();
}
//Implementing operator +.
RectPrism RectPrism::operator + (const RectPrism& rectp){
  double final_width = width_ + rectp.getWidth();
  double final_length = length_ + rectp.getLength();
  double final_height = height_ + rectp.getHeight();
  return RectPrism(final_width, final_length, final_height);
}
//Implementing operator -.
RectPrism RectPrism::operator - (const RectPrism& rectp){
  double final_width = (0 > width_ - rectp.getWidth())? 0: width_ - rectp.getWidth();
  double final_length = (0 > length_ - rectp.getLength())? 0: length_ - rectp.getLength();
  double final_height = (0 > height_ - rectp.getHeight())? 0: height_ - rectp.getHeight();
  return RectPrism(final_width, final_length, final_height);
}
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here

  ifstream ifs(file_name, std::ifstream::in);
  int no_objects;
  ifs >> no_objects;
  vector<Shape*> v;
  if (no_objects == 0) return v;
  for (int i = 0; i < no_objects; i++){
    string name;
    ifs >> name;
    if (name == "Rectangle"){
        // Creating a rectangle object.
        double rec_width, rec_length;
        ifs >> rec_width >> rec_length;
        Shape* rec_ptr = new Rectangle(rec_width, rec_length);
        v.push_back(rec_ptr);
      }

    else if (name == "Circle"){
        //Creating a circle object.
        double cir_radius;
        ifs >> cir_radius;
        Shape* cir_ptr = new Circle(cir_radius);
        v.push_back(cir_ptr);
      }

    else if (name == "Sphere"){
        //Creating a sphere object.
        double sph_radius;
        ifs >> sph_radius;
        Shape* sph_ptr = new Sphere(sph_radius);
        v.push_back(sph_ptr);
      }

    else if (name == "RectPrism"){
        //Creating a rectprism object.
        double rp_width, rp_length, rp_height;
        ifs >> rp_width >> rp_length >> rp_height;
        Shape* rp_ptr = new RectPrism(rp_width, rp_length, rp_height);
        v.push_back(rp_ptr);
      }

}
  ifs.close();
	return v; // please remeber to modify this line to return the correct value
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
  for (int i=0; i<shapes.size(); i++){
    double cur_area = shapes[i] -> getArea();
    if (cur_area > max_area) max_area = cur_area;
  }

	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
  for (int i=0; i<shapes.size(); i++){
    double cur_volume = shapes[i] -> getVolume();
    if (cur_volume > max_volume) max_volume = cur_volume;
  }
	return max_volume;
}
