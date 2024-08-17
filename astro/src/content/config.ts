import { defineCollection, z } from 'astro:content';

const blog = defineCollection({
	type: 'content',
	// Type-check frontmatter using a schema
	schema: z.object({
		id: z.string().optional(),
		title: z.string(),
		description: z.string(),
		// Transform string to Date object
		pubDate: z.coerce.date(),
		updatedDate: z.coerce.date().optional(),
		heroImage: z.string().optional(),
		minutesRead: z.string().optional(),
		file: z.string().optional(),
		isError: z.boolean().optional(),
	}),
});

export const collections = { blog };
