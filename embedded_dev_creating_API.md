Creating an API for embedded development involves several best practices to ensure it is effective and reusable. Here are some key tips:

- Start with a draft API and expect it to evolve over time. Typically, an API stabilizes after three to four projects, with minimal changes in subsequent iterations.
- When designing an API for multiple microcontroller vendors, examine the same peripheral across different microcontrollers and list both common and uncommon features. Common features should be included in the API, while uncommon features can be implemented as extensions if necessary.
- Aim to keep the number of interfaces per module to no more than ten, as the human mind can only consistently remember approximately 10-12 pieces of information that belong together.
Use logical naming conventions that allow developers to easily recognize and recall API interfaces. Cryptic naming can lead to confusion and difficulty in remembering the purpose of the API.
- Provide a method for extending the interface to accommodate uncommon features that developers may need, ensuring the API remains flexible and adaptable.

For embedded systems, APIs are crucial for enabling software to be reused across different projects and microcontrollers. They should be designed with clear instructions and logical structures to ensure they are easy to understand and use.

Additionally, it's important to understand that there is no one-size-fits-all API for all embedded systems. Different microcontrollers and development frameworks may require different approaches to API design and implementation.

For further learning and resources on API and HAL design, consider attending Jacob's free DesignNews Digikey Continuing Education Course or checking out his book on Reusable Firmware Development.