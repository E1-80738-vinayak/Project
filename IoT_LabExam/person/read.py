
import person.connection as db

def get_person():
    connection=db.get_connection()

    query=f"select * from tracker;"
    
    cursor=connection.cursor()
    cursor.execute(query)
    persons=cursor.fetchall()

    cursor.close()
    connection.close()

    return persons