#include "Score.h"

Score::Score()
{
	entityId = "Score";
	InitializeEntity(this);

	zero = new Model("Assets/Models/Score/largefont0.ply");
	one = new Model("Assets/Models/Score/largefont1.ply");
	two = new Model("Assets/Models/Score/largefont2.ply");
	three = new Model("Assets/Models/Score/largefont3.ply");
	four = new Model("Assets/Models/Score/largefont4.ply");
	five = new Model("Assets/Models/Score/largefont5.ply");
	six = new Model("Assets/Models/Score/largefont6.ply");
	seven = new Model("Assets/Models/Score/largefont7.ply");
	eight = new Model("Assets/Models/Score/largefont8.ply");
	nine = new Model("Assets/Models/Score/largefont9.ply");

	zero->transform.SetScale(glm::vec3(fontSize));
	one->transform.SetScale(glm::vec3(fontSize));
	two->transform.SetScale(glm::vec3(fontSize));
	three->transform.SetScale(glm::vec3(fontSize));
	four->transform.SetScale(glm::vec3(fontSize));
	five->transform.SetScale(glm::vec3(fontSize));
	six->transform.SetScale(glm::vec3(fontSize));
	seven->transform.SetScale(glm::vec3(fontSize));
	eight->transform.SetScale(glm::vec3(fontSize));
	nine->transform.SetScale(glm::vec3(fontSize));

	PrintNumber(0);
}

void Score::AddScore(int score)
{
	currentScore += score;

	PrintNumber(currentScore);
}

void Score::Start()
{
}

void Score::Update(float deltaTime)
{
}

void Score::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
}

void Score::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void Score::PrintNumber(int number)
{
	for (Model* model : scoreModels)
	{
		renderer->RemoveModel(model);
		delete model;
	}

	scoreModels.clear();

	std::vector<int> scoreDigits;

	if (number == 0)
	{
		scoreDigits.push_back(0);
	}
	else
	{
		while (number > 0)
		{
			int digit = number % 10;
			scoreDigits.insert(scoreDigits.begin(), digit);
			number /= 10;
		}
	}

	
	for(int i = 0; i < scoreDigits.size(); i++)
	{
		Model* scoreDigit = new Model();

		switch (scoreDigits[i])
		{

		case 0:
			scoreDigit->CopyFromModel(*zero);
			break;

		case 1:
			scoreDigit->CopyFromModel(*one);
			break;

		case 2:
			scoreDigit->CopyFromModel(*two);
			break;

		case 3:
			scoreDigit->CopyFromModel(*three);
			break;

		case 4:
			scoreDigit->CopyFromModel(*four);
			break;

		case 5:
			scoreDigit->CopyFromModel(*five);
			break;

		case 6:
			scoreDigit->CopyFromModel(*six);
			break;

		case 7:
			scoreDigit->CopyFromModel(*seven);
			break;

		case 8:
			scoreDigit->CopyFromModel(*eight);
			break;

		case 9:
			scoreDigit->CopyFromModel(*nine);
			break;

		}
		
		scoreDigit->transform.SetPosition(glm::vec3(posX + (i * digitSpacing), posY, 0));
		renderer->AddModel(scoreDigit, shader);
		scoreModels.push_back(scoreDigit);
	}
}

