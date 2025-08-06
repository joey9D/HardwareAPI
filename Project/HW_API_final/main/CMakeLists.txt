# ESP-IDF Main Component
# ChatGPT Empfehlung: main.cpp als ESP-IDF Hauptkomponente

# ESP-IDF Main Komponente registrieren
idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS "."
    REQUIRES hw_api
)

message(STATUS "Main ESP-IDF component registered successfully")
