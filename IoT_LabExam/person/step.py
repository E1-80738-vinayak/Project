
import person.connection as db

def get_step():
    connection=db.get_connection()

    query=f"select MAX(step_detection) from tracker;"
    
    cursor=connection.cursor()
    cursor.execute(query)
    persons=cursor.fetchall()

    cursor.close()
    connection.close()

    return persons