// Funzione per creare una sezione HTML
function createSection(content, containerId) {
    const container = document.getElementById(containerId);
    if (!container) return;

    const titleElement = document.createElement("h1");
    titleElement.className = "display-5";
    titleElement.textContent = content.title;

    const descElement = document.createElement("p");
    descElement.className = "lead text-muted";
    descElement.textContent = content.description;

    container.appendChild(titleElement);
    container.appendChild(descElement);
}

// Funzione per creare l'elenco dei termini
function createGlossaryList(terms, containerId) {
    const container = document.getElementById(containerId);
    if (!container) return;

    terms.forEach(termData => {
        const item = document.createElement("a");
        item.href = "#";
        item.className = "list-group-item list-group-item-action";

        const termElement = document.createElement("h5");
        termElement.className = "mb-1";
        termElement.textContent = termData.term;

        const definitionElement = document.createElement("p");
        definitionElement.className = "mb-1";
        definitionElement.textContent = termData.definition;

        item.appendChild(termElement);
        item.appendChild(definitionElement);
        container.appendChild(item);
    });
}

// Popolamento della pagina
window.onload = () => {
    createSection(glossaryData.titleSection, "title-section");
    createGlossaryList(glossaryData.terms, "glossary-list");
};
