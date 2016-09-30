//Interface
//Copyright (c) Lebin Mathew Alex. All rights reserved.

interface IDisplay
{
	public int x = 3;
	public void Display();
	public void Display2();
}

class Simple implements IDisplay
{
	public void fisplay()
	{
		System.out.println(x);
	}
	
	public void Display(){};
	public void Display2(){};
}

public class Interface
{
	public static void main(String[] args)
	{
		Simple s = new Simple();
		s.Display();
	}
}
