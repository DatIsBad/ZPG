#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/glm.hpp>

#include <vector>
#include <memory>
#include <iostream>



class Transformation
{
public:
	Transformation();

	// Method to add a transformation using shared_ptr
	void addTransformation(const std::shared_ptr<Transformation>& transformation);

	template<typename T, typename... Args>
	void addTrans(Args&&... args) {
		static_assert(std::is_base_of<Transformation, T>::value, "T must be a Transformation");
		m_TransVector.push_back(std::make_shared<T>(std::forward<Args>(args)...));
	}
	glm::mat4 getValue() const;
	virtual glm::mat4 getValued() const;

	virtual ~Transformation() = default;
private:
	std::vector<std::shared_ptr<Transformation>> m_TransVector;
};




#endif // TRANSFORMATION_H