from flask import Flask, request, jsonify
import sympy as sp

app = Flask(__name__, static_url_path='', static_folder='static')

@app.route('/integrate', methods=['POST'])
def integrate():
    data = request.json
    equation = data.get('equation')
    lower_limit = data.get('lower_limit', 0)
    upper_limit = data.get('upper_limit', 2)
    
    # Define the variable
    x = sp.symbols('x')
    
    # Parse the equation
    f = sp.sympify(equation)
    
    # Integrate the function
    integral_f = sp.integrate(f, (x, lower_limit, upper_limit))
    
    return jsonify({
        'equation': equation,
        'integral': str(integral_f),
        'limits': f'{lower_limit} to {upper_limit}'
    })

@app.route('/differentiate', methods=['POST'])
def differentiate():
    data = request.json
    equation = data.get('equation')
    
    # Define the variable
    x = sp.symbols('x')
    
    # Parse the equation
    f = sp.sympify(equation)
    
    # Differentiate the function
    derivative_f = sp.diff(f, x)
    
    return jsonify({
        'equation': equation,
        'derivative': str(derivative_f)
    })

if __name__ == '__main__':
    app.run(debug=True)
