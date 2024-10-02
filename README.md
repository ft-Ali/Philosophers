# Philosophers


# Mutex en C

Un **mutex** (ou *mutual exclusion*) est un mécanisme de synchronisation utilisé pour éviter que plusieurs threads accèdent simultanément à une ressource partagée, garantissant ainsi la cohérence des données.

| Concept         | Description                                                                                  |
|-----------------|----------------------------------------------------------------------------------------------|
| **Définition**   | Un mutex est un verrou qui permet de contrôler l'accès à une ressource partagée entre plusieurs threads. |
| **Verrouillage** | Un thread doit "verrouiller" (lock) le mutex avant d'accéder à la ressource partagée.         |
| **Déverrouillage** | Après avoir terminé son travail, le thread "déverrouille" (unlock) le mutex pour libérer la ressource. |
| **Utilisation**  | Protéger les sections critiques, où plusieurs threads pourraient altérer ou lire des données simultanément. |
| **Avantage**     | Empêche les *conditions de course* (race conditions) et assure la synchronisation entre threads. |
| **Limitation**   | Synchronise uniquement les threads au sein du même processus. Pour des processus distincts, d'autres mécanismes sont nécessaires. |

### Pourquoi utiliser des mutex ?
Les mutex permettent de garantir que les ressources partagées ne sont accessibles qu'à un seul thread à la fois, évitant ainsi les corruptions de données dans les environnements multithreadés.

---

**Note** : Les mutex font partie des primitives de synchronisation essentielles pour la programmation concurrente en C.
