import person.connection as db
def insert_person(name,age,city,step,pulse,oxygen,body):
    connection=db.get_connection()

    query= f"insert into tracker values (\"{name}\",{age},\"{city}\",{step},{pulse},{oxygen},{body});"
    
    cursor = connection.cursor()
    cursor.execute(query)
    connection.commit()

    cursor.close()
    connection.close()