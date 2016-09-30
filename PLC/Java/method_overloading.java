//Method Overloading
//Copyright (c) Lebin Mathew Alex. All rights reserved.

import java.util.*;

class Shape
{	
	static float Area(float r)
	{
		return 3.14f *r*r;
	}
	
	static float Area(float l, float b)
	{
		return l*b;
	}
	
	static String Area(String s1, String s2)
	{
		return s1+s2;
	}
}

public class Overload
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		System.out.println("Enter Strings :\n");
		String s1 = scan.nextLine();
		String s2 = scan.nextLine();
		System.out.println(Shape.Area(2.4f));
		System.out.println(Shape.Area(1.1f, 2.0f));
		String a = Shape.Area(s1, s2);
		System.out.println(Shape.Area(s1, s2));
	}
}
