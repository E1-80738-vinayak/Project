import person.connection as db

def update_person(name,pulse):
    connection= db.get_connection()

    query = f"update tracker set pulse={pulse} where name= \"{name}\";"

    cursor = connection.cursor()
    cursor.execute(query)
    connection.commit()

    cursor.close()
    connection.close()

