
import person.connection as db

def info(name):
    connection=db.get_connection()

    query=f"select * from tracker where name=\"{name}\";"
    
    cursor=connection.cursor()
    cursor.execute(query)
    persons=cursor.fetchall()

    cursor.close()
    connection.close()

    return persons