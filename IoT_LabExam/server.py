from flask import Flask, request

import person.read
import person.update
import person.info
import person.insert
import person.step

app=Flask(__name__)

@app.route("/add",methods = {'POST'})
def insert_person():
    
    name=request.form.get('name')
    age=request.form.get('age')
    city=request.form.get('city')
    step=request.form.get('step')
    pulse=request.form.get('pulse')
    oxygen=request.form.get('oxygen')    
    body=request.form.get('body')
    person.insert.insert_person(name,age,city,step,pulse,oxygen,body)
    
    return "person is added into database successfully"

@app.route("/all",methods ={'GET'})
def read_person():
    persons=person.read.get_person()
    print("person list")
    for per in persons:
        print(per)
    return persons

@app.route("/update",methods ={'PUT'})
def update_person():
    name=request.form.get('name')
    pulse=request.form.get('pulse')
    person.update.update_person(name,pulse)
    return "person is updated in database successfully"

@app.route("/info",methods ={'GET'})
def info():
    name=request.form.get('name')
    persons=person.info.info(name)
    print("person list")
    for per in persons:
        print(per)
    return persons
    
    return "person successfully found from database"
@app.route("/step",methods ={'GET'})
def get_step():
    persons=person.step.get_step()
    print("persons")
    return persons
    return "person successfully found from database"

# run server
app.run(debug=True)