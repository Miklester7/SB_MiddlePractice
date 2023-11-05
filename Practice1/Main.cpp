
#include <iostream>
#include <iomanip>
#include <string>

struct Vector
{
public:
	Vector(const int X, const int Y, const int Z) : x(X), y(Y), z(Z) {};

	Vector() = delete;
	int x;
	int y;
	int z;

	Vector& operator *(const int& Value)
	{
		x *= Value;
		y *= Value;
		z *= Value;

		return *this;
	}

	Vector& operator - (const Vector& vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;

		return *this;
	}
	
	friend std::istream& operator >> (std::istream& is, Vector& vector)
	{
		is >> vector.x >> vector.y >> vector.z;
		return is;
	}
};

class Grid
{
public:

	Grid(const int InRow, const int InCol,std::string* Name) : Row(InRow), Col(InCol)
	{
		GridName = new std::string(*Name);

		InitArray();
	};

	Grid(const int Size, std::string* Name) : Row(Size), Col(Size) 
	{
		GridName = new std::string(*Name);

		InitArray();
	};

	Grid(const Grid& grid)
	{
		Row = grid.Row;
		Col = grid.Col;

		GridName = new std::string(*grid.GridName);

		Array2D = new int* [Row];
		for (int i = 0; i < Row; ++i)
		{
			Array2D[i] = new int[Col];
		}

		for (int i = 0; i < Row; ++i)
		{
			for (int j = 0; j < Col; ++j)
			{
				Array2D[i][j] = grid.Array2D[i][j];
			}
		}
		if(grid.JustVector)
		{
			JustVector = new Vector(*grid.JustVector);
		}
	}

	Grid() = delete;

	
	~Grid()
	{
		delete GridName;
		
		if (JustVector) delete JustVector;

		for (int i = 0; i < Row; ++i)
		{
			delete[] Array2D[i];
		}

		delete[] Array2D;
	}

	Grid& operator = (const Grid& grid)
	{
		Row = grid.Row;
		Col = grid.Col;

		if (GridName)
		{
			delete GridName;
		}
		GridName = new std::string(*grid.GridName);

		if (Array2D)
		{
			for (int i = 0; i < Row; ++i)
			{
				delete[] Array2D[i];
			}

			delete[] Array2D;
		}

		Array2D = new int* [Row];
		for (int i = 0; i < Row; ++i)
		{
			Array2D[i] = new int[Col];
		}

		for (int i = 0; i < Row; ++i)
		{
			for (int j = 0; j < Col; ++j)
			{
				Array2D[i][j] = grid.Array2D[i][j];
			}
		}

		if (grid.JustVector)
		{
			if (JustVector) delete JustVector;
			JustVector = new Vector(*grid.JustVector);
		}
		
		return *this;
	}

	friend std::ostream& operator <<(std::ostream& out, const Grid& grid)
	{
		for (int i = 0; i <grid.Row; ++i)
		{
			for (int j = 0; j < grid.Col; ++j)
			{
				out << std::setw(5) << grid.Array2D[i][j] ;
			}

			out << std::endl;
		}

		return out;
	}

	void SetVectorValue(const Vector* value)
	{
		if (JustVector)
		{
			delete JustVector;
		}

		JustVector = new Vector(*value);
	}

	const std::string VectorToString()
	{
		return JustVector ? "X=" + std::to_string(JustVector->x) + " " +
			"Y=" + std::to_string(JustVector->y) + " " + "Z=" + std::to_string(JustVector->z) + " " :
			"Vector is nullptr";
	}

private:
	int Row;
	int Col;

	std::string* GridName;
	Vector* JustVector = nullptr;

	int** Array2D;

private:
	void InitArray()
	{
		Array2D = new int* [Row];
		for (int i = 0; i < Row; ++i)
		{
			Array2D[i] = new int[Col];
		}

		for (int i = 0; i < Row; ++i)
		{
			for (int j = 0; j < Col; ++j)
			{
				Array2D[i][j] = rand() % 20 - 10;
			}
		}
	}


};

int main()
{
	std::string GridName1 = "grid1";

	Grid grid1(5, &GridName1);

	Grid grid2(grid1);

	const Vector vector(1, 2, 3);
	grid2.SetVectorValue(&vector);

	Grid grid3 = grid2;

	std::cout << grid1 <<std::endl<< grid2 << std::endl << grid3;

	std::cout << grid1.VectorToString() << std::endl << grid2.VectorToString() << std::endl << grid3.VectorToString() << std::endl;

	return 0;
}