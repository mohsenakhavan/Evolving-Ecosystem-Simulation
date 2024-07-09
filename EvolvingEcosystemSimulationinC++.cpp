#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <memory>
#include <fstream>

// Forward declarations
class Creature;
class Environment;
class NeuralNetwork;

// Utility functions
double random(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

// Neural Network implementation
class NeuralNetwork {
private:
    std::vector<std::vector<std::vector<double>>> weights;
    std::vector<std::vector<double>> biases;
    
public:
    NeuralNetwork(const std::vector<int>& layerSizes) {
        for (size_t i = 1; i < layerSizes.size(); ++i) {
            weights.push_back(std::vector<std::vector<double>>(
                layerSizes[i],
                std::vector<double>(layerSizes[i-1])
            ));
            biases.push_back(std::vector<double>(layerSizes[i]));
            
            for (auto& neuron : weights.back()) {
                for (auto& w : neuron) {
                    w = random(-1, 1);
                }
            }
            for (auto& b : biases.back()) {
                b = random(-1, 1);
            }
        }
    }
    
    std::vector<double> feedForward(const std::vector<double>& input) {
        std::vector<double> activations = input;
        
        for (size_t i = 0; i < weights.size(); ++i) {
            std::vector<double> newActivations(weights[i].size());
            
            for (size_t j = 0; j < weights[i].size(); ++j) {
                double sum = 0;
                for (size_t k = 0; k < activations.size(); ++k) {
                    sum += weights[i][j][k] * activations[k];
                }
                newActivations[j] = std::tanh(sum + biases[i][j]);
            }
            
            activations = std::move(newActivations);
        }
        
        return activations;
    }
    
    void mutate(double rate) {
        for (auto& layer : weights) {
            for (auto& neuron : layer) {
                for (auto& w : neuron) {
                    if (random(0, 1) < rate) w += random(-0.1, 0.1);
                }
            }
        }
        for (auto& layer : biases) {
            for (auto& b : layer) {
                if (random(0, 1) < rate) b += random(-0.1, 0.1);
            }
        }
    }
};

// Creature class
class Creature {
private:
    NeuralNetwork brain;
    double energy;
    double x, y;
    
public:
    Creature() : brain({3, 5, 2}), energy(100), x(random(0, 100)), y(random(0, 100)) {}
    
    void think(const Environment& env);
    void update(const Environment& env);
    
    double getEnergy() const { return energy; }
    double getX() const { return x; }
    double getY() const { return y; }
    
    std::unique_ptr<Creature> reproduce() {
        auto child = std::make_unique<Creature>(*this);
        child->brain.mutate(0.1);
        child->energy = 50;
        energy -= 50;
        return child;
    }
};

// Environment class
class Environment {
private:
    std::vector<std::unique_ptr<Creature>> creatures;
    std::vector<std::pair<double, double>> foodSources;
    int day;
    
public:
    Environment(int numCreatures, int numFoodSources) : day(0) {
        for (int i = 0; i < numCreatures; ++i) {
            creatures.push_back(std::make_unique<Creature>());
        }
        for (int i = 0; i < numFoodSources; ++i) {
            foodSources.emplace_back(random(0, 100), random(0, 100));
        }
    }
    
    void update();
    void spawnFood();
    std::vector<double> getClosestFood(double x, double y) const;
    
    int getDay() const { return day; }
    int getPopulation() const { return creatures.size(); }
};

// Creature method implementations
void Creature::think(const Environment& env) {
    auto foodInfo = env.getClosestFood(x, y);
    std::vector<double> input = {energy / 100, foodInfo[0] / 100, foodInfo[1] / 100};
    auto output = brain.feedForward(input);
    
    double dx = output[0] * 5;
    double dy = output[1] * 5;
    
    x = std::clamp(x + dx, 0.0, 100.0);
    y = std::clamp(y + dy, 0.0, 100.0);
    
    energy -= 1 + (std::abs(dx) + std::abs(dy)) / 10;
}

void Creature::update(const Environment& env) {
    auto foodInfo = env.getClosestFood(x, y);
    if (foodInfo[0] < 1 && foodInfo[1] < 1) {
        energy += 50;
    }
}

// Environment method implementations
void Environment::update() {
    for (auto& creature : creatures) {
        creature->think(*this);
        creature->update(*this);
    }
    
    creatures.erase(
        std::remove_if(creatures.begin(), creatures.end(),
            [](const auto& c) { return c->getEnergy() <= 0; }),
        creatures.end());
    
    for (auto it = creatures.begin(); it != creatures.end(); ) {
        if ((*it)->getEnergy() >= 150) {
            it = creatures.insert(it, (*it)->reproduce());
            ++it;
        }
        ++it;
    }
    
    spawnFood();
    ++day;
}

void Environment::spawnFood() {
    if (random(0, 1) < 0.1) {
        foodSources.emplace_back(random(0, 100), random(0, 100));
    }
}

std::vector<double> Environment::getClosestFood(double x, double y) const {
    double closestDist = std::numeric_limits<double>::max();
    std::vector<double> closest(2);
    
    for (const auto& food : foodSources) {
        double dx = food.first - x;
        double dy = food.second - y;
        double dist = std::sqrt(dx*dx + dy*dy);
        
        if (dist < closestDist) {
            closestDist = dist;
            closest[0] = dx;
            closest[1] = dy;
        }
    }
    
    return closest;
}



int main() {
    Environment env(50, 20);
    std::ofstream dataFile("ecosystem_data.csv");
    dataFile << "Day,Population\n";
    
    for (int i = 0; i < 20; ++i) {  // Changed to run for 20 days
        env.update();
        
        // Display and save results every day
        std::cout << "Day " << env.getDay() << ": Population " << env.getPopulation() << std::endl;
        dataFile << env.getDay() << "," << env.getPopulation() << "\n";
    }
    
    dataFile.close();
    std::cout << "Simulation complete. Data saved to ecosystem_data.csv" << std::endl;
    
    return 0;
}