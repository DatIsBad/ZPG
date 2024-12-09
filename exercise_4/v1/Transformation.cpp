#include "Transformation.h"

Transformation::Transformation() {

}

// Method to add a transformation using shared_ptr
void Transformation::addTransformation(const std::shared_ptr<Transformation>& transformation) {
    m_TransVector.push_back(transformation);
}


glm::mat4 Transformation::getValued() const {
    return glm::mat4(1.0f);
}



glm::mat4 Transformation::getValue() const {
    glm::mat4 m_value = glm::mat4(1.0f);

    for (const auto& transformation : m_TransVector) {
        m_value = transformation->getValued() * m_value; // Apply transformations in order
    }

    return m_value;
}