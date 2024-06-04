import pytest
from app import app

@pytest.fixture
def client():
    app.testing = True
    return app.test_client()

def test_integrate(client):
    response = client.post('/integrate', json={'equation': 'x**2'})
    data = response.get_json()
    assert data['integral'] == '8/3'

def test_differentiate(client):
    response = client.post('/differentiate', json={'equation': 'x**3'})
    data = response.get_json()
    assert data['derivative'] == '3*x**2'
