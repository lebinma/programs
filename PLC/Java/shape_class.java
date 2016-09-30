//Shape
//Copyright (c) Lebin Mathew Alex. All rights reserved.

import java.util.Scanner;

class Shape
{
	static final float pi = 3.14f;
	float area;
	Scanner scan = new Scanner(System.in);
	
	void Display()
	{
		System.out.println("\nArea = " + area + " Sq.cm");
	}
}

class Rectangle extends Shape
{
	float length, breadth;
	
	Rectangle()
	{
		System.out.println("\nEnter length & breadth :");
		length = scan.nextFloat();
		breadth = scan.nextFloat();	
		this.area = length * breadth;
	}
}

class Square extends Shape
{
	float side;
	
	Square()
	{
		System.out.println("\nEnter length of side :");
		side = scan.nextFloat();
		this.area = side * side;
	}
}

class Elipse extends Shape
{
	float major, minor;
	
	Elipse()
	{
		System.out.println("\nEnter major & minor axis length :");
		major = scan.nextFloat();
		minor = scan.nextFloat();	
		this.area = pi * major * minor;
	}
}

class Triangle extends Shape
{
	float breadth, height;
	
	Triangle()
	{
		System.out.println("\nEnter breadth & height :");
		breadth = scan.nextFloat();
		height = scan.nextFloat();	
		this.area = 0.5f * breadth * height;
	}
}

class Circle extends Shape
{
	float radius;
	
	Circle()
	{
		System.out.println("\nEnter radius :");
		radius = scan.nextFloat();
		this.area = pi * radius * radius;
	}
}

public class ShapeClass
{
	public static void main(String args[])
	{
		int choice, c;
		Scanner scan = new Scanner(System.in);
		
		do
		{
			System.out.println("\n1 Rectangle\n2 Square\n3 Elipse");
			System.out.println("4 Triangle\n5 Circle\n\nEnter choice :");
			choice = scan.nextInt();
			
			switch (choice)
			{
				case 1 : 
					Rectangle rect = new Rectangle();
					rect.Display();
					break;
					
				case 2 : 
					Square sq = new Square();
					sq.Display();
					break;
					
				case 3 : 
					Elipse el = new Elipse();
					el.Display();
					break;
					
				case 4 : 
					Triangle tr = new Triangle();
					tr.Display();
					break;
					
				case 5 : 
					Circle cir = new Circle();
					cir.Display();
					break;
				
				default : System.out.println("\nInvalid choice!!!!");
			}
			
			System.out.println("\nPress 1 to try again...");
			c = scan.nextInt();
		
		} while (c == 1);
	}
}
