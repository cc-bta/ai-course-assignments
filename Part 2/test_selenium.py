from selenium import webdriver
import time
import pytest

@pytest.fixture(scope="module")
def driver():
    # Replace 'path/to/chromedriver' with the actual path to the chromedriver executable
    driver = webdriver.Chrome(executable_path='path/to/chromedriver')
    yield driver
    driver.quit()

def test_integrate(driver):
    driver.get("http://127.0.0.1:5000")
    
    equation_input = driver.find_element_by_id("equation")
    equation_input.send_keys("x^2")
    
    integrate_button = driver.find_element_by_xpath("//button[text()='Integrate']")
    integrate_button.click()
    
    time.sleep(2)  # Wait for the result to be displayed
    
    result = driver.find_element_by_id("result").text
    assert "Integral of x^2 from 0 to 2: 8/3" in result

def test_differentiate(driver):
    driver.get("http://127.0.0.1:5000")
    
    equation_input = driver.find_element_by_id("equation")
    equation_input.send_keys("x^3")
    
    differentiate_button = driver.find_element_by_xpath("//button[text()='Differentiate']")
    differentiate_button.click()
    
    time.sleep(2)  # Wait for the result to be displayed
    
    result = driver.find_element_by_id("result").text
    assert "Derivative of x^3: 3*x**2" in result
