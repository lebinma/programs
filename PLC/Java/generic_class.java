//Generic Class
//Copyright (c) Lebin Mathew Alex. All rights reserved.

class Number <T>
{ 
	Integer i1, i2;
	Double d1, d2;
	String s1, s2, sum;
	
	Number(T a, T b)
	{
		if (a instanceof Integer && b instanceof Integer)
		{
			i1 = (Integer) a;
			i2 = (Integer) b;
			sum = (new Integer(i1.intValue() + i2.intValue())).toString();
		}
		else if (a instanceof Double && b instanceof Double)
		{
			d1 = (Double) a;
			d2 = (Double) b;
			sum = (new Double(d1.floatValue() + d2.floatValue())).toString();
		}
		
		else if (a instanceof String && b instanceof String)
		{
			s1 = (String) a;
			s2 = (String) b;
			sum = s1 + s2;
		}
	}
	
	void Add()
	{
		System.out.println(sum);
	}
}

public class Generic
{
	public static void main(String[] args)
	{
		Number<Integer> n1 = new Number<Integer>(5, 4);
		Number<Double> n2 = new Number<Double>(4.2d, 1.2d);
		Number<String> n3 = new Number<String>("Hello", " There");
		
		n1.Add();
		n2.Add();
		n3.Add();
	}
}
