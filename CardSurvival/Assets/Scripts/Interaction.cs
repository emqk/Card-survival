using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Interaction : MonoBehaviour
{
    Camera playerCamera;

    Card currentCard = null;
    float cardDefaultY = -1;

    // Start is called before the first frame update
    void Awake()
    {
        playerCamera = GetComponent<Camera>();
    }

    // Update is called once per frame
    void Update()
    {
        RaycastHit hit;
        Ray ray = playerCamera.ScreenPointToRay(Input.mousePosition);

        if (Physics.Raycast(ray, out hit))
        {
            Card card = hit.transform.GetComponent<Card>();
            if (card)
            {
                if (Input.GetKeyDown(KeyCode.Mouse0))
                {
                    currentCard = card;
                    cardDefaultY = currentCard.transform.position.y;
                }
            }
        }

        if (currentCard)
        {
            Vector3 newPosition = new Vector3(hit.point.x, cardDefaultY + 1, hit.point.z);
            currentCard.transform.position = newPosition;
        }

        if (Input.GetKeyUp(KeyCode.Mouse0))
        {
            currentCard.transform.position = new Vector3(Mathf.Round(hit.point.x), cardDefaultY, Mathf.Round(hit.point.z));
            currentCard = null;
        }
    }
}
