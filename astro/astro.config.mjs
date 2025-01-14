import { defineConfig } from 'astro/config';
import mdx from '@astrojs/mdx';

import sitemap from '@astrojs/sitemap';

import { remarkReadingTime } from './src/reading-time.ts';
import remarkGFM from 'remark-gfm';

// https://astro.build/config
export default defineConfig({
	site: 'https://karelsyrovy.cz',
	markdown: {
		remarkPlugins: [remarkReadingTime, remarkGFM],
		extendDefaultPlugins: true,
		shikiConfig: {
		  theme: 'dracula',
		},
	  },
	integrations: [mdx({remarkPlugins: [remarkGFM], gfm: true}), sitemap()],
	outDir: '../dist',
});
